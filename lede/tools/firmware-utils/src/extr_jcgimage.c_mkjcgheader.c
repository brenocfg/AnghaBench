#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
typedef  long uLong ;
typedef  scalar_t__ time_t ;
struct jcg_header {void* jh_hcrc; void* jh_dcrc; void* jh_minor; void* jh_major; void* jh_time; void* jh_type; void* jh_magic; } ;

/* Variables and functions */
 long JH_MAGIC ; 
 void* Z_NULL ; 
 long crc32 (long,void*,int) ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 void* htonl (long) ; 
 void* htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct jcg_header*,int /*<<< orphan*/ ,int) ; 
 int source_date_epoch ; 
 int sscanf (char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ time (scalar_t__*) ; 

void
mkjcgheader(struct jcg_header *h, size_t psize, char *version)
{
	uLong crc;
	uint16_t major = 0, minor = 0;
	void *payload = (void *)h + sizeof(*h);
	time_t t;

	if (source_date_epoch != -1) {
		t = source_date_epoch;
	} else if ((time(&t) == (time_t)(-1))) {
		err(1, "time call failed");
	}

	if (version != NULL) {
		if (sscanf(version, "%hu.%hu", &major, &minor) != 2) {
			err(1, "cannot parse version \"%s\"", version);
		}
	}

	memset(h, 0, sizeof(*h));
	h->jh_magic = htonl(JH_MAGIC);
	h->jh_type  = htonl(1);
	h->jh_time  = htonl(t);
	h->jh_major = htons(major);
	h->jh_minor = htons(minor);

	/* CRC over JCG payload (uImage) */
	crc = crc32(0L, Z_NULL, 0);
	crc = crc32(crc, payload, psize);
	h->jh_dcrc  = htonl(crc);

	/* CRC over JCG header */
	crc = crc32(0L, Z_NULL, 0);
	crc = crc32(crc, (void *)h, sizeof(*h));
	h->jh_hcrc  = htonl(crc);
}