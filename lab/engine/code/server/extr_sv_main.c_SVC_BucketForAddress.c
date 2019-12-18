#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int type; int /*<<< orphan*/  ip6; int /*<<< orphan*/  ip; } ;
typedef  TYPE_2__ netadr_t ;
struct TYPE_10__ {int /*<<< orphan*/  _6; int /*<<< orphan*/  _4; } ;
struct TYPE_12__ {int type; int lastTime; size_t hash; struct TYPE_12__* prev; struct TYPE_12__* next; scalar_t__ burst; TYPE_1__ ipv; } ;
typedef  TYPE_3__ leakyBucket_t ;

/* Variables and functions */
 int /*<<< orphan*/  Com_Memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Com_Memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int MAX_BUCKETS ; 
 int NA_BAD ; 
#define  NA_IP 129 
#define  NA_IP6 128 
 long SVC_HashForAddress (TYPE_2__) ; 
 int Sys_Milliseconds () ; 
 TYPE_3__** bucketHashes ; 
 TYPE_3__* buckets ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static leakyBucket_t *SVC_BucketForAddress( netadr_t address, int burst, int period ) {
	leakyBucket_t	*bucket = NULL;
	int						i;
	long					hash = SVC_HashForAddress( address );
	int						now = Sys_Milliseconds();

	for ( bucket = bucketHashes[ hash ]; bucket; bucket = bucket->next ) {
		switch ( bucket->type ) {
			case NA_IP:
				if ( memcmp( bucket->ipv._4, address.ip, 4 ) == 0 ) {
					return bucket;
				}
				break;

			case NA_IP6:
				if ( memcmp( bucket->ipv._6, address.ip6, 16 ) == 0 ) {
					return bucket;
				}
				break;

			default:
				break;
		}
	}

	for ( i = 0; i < MAX_BUCKETS; i++ ) {
		int interval;

		bucket = &buckets[ i ];
		interval = now - bucket->lastTime;

		// Reclaim expired buckets
		if ( bucket->lastTime > 0 && ( interval > ( burst * period ) ||
					interval < 0 ) ) {
			if ( bucket->prev != NULL ) {
				bucket->prev->next = bucket->next;
			} else {
				bucketHashes[ bucket->hash ] = bucket->next;
			}
			
			if ( bucket->next != NULL ) {
				bucket->next->prev = bucket->prev;
			}

			Com_Memset( bucket, 0, sizeof( leakyBucket_t ) );
		}

		if ( bucket->type == NA_BAD ) {
			bucket->type = address.type;
			switch ( address.type ) {
				case NA_IP:  Com_Memcpy( bucket->ipv._4, address.ip, 4 );   break;
				case NA_IP6: Com_Memcpy( bucket->ipv._6, address.ip6, 16 ); break;
				default: break;
			}

			bucket->lastTime = now;
			bucket->burst = 0;
			bucket->hash = hash;

			// Add to the head of the relevant hash chain
			bucket->next = bucketHashes[ hash ];
			if ( bucketHashes[ hash ] != NULL ) {
				bucketHashes[ hash ]->prev = bucket;
			}

			bucket->prev = NULL;
			bucketHashes[ hash ] = bucket;

			return bucket;
		}
	}

	// Couldn't allocate a bucket for this address
	return NULL;
}