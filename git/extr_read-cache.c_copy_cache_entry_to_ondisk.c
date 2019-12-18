#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_10__ {void* nsec; void* sec; } ;
struct TYPE_8__ {void* nsec; void* sec; } ;
struct ondisk_cache_entry {scalar_t__ data; void* size; void* gid; void* uid; void* mode; void* ino; void* dev; TYPE_3__ mtime; TYPE_1__ ctime; } ;
struct TYPE_13__ {int /*<<< orphan*/  hash; } ;
struct TYPE_11__ {int /*<<< orphan*/  nsec; int /*<<< orphan*/  sec; } ;
struct TYPE_9__ {int /*<<< orphan*/  nsec; int /*<<< orphan*/  sec; } ;
struct TYPE_12__ {int /*<<< orphan*/  sd_size; int /*<<< orphan*/  sd_gid; int /*<<< orphan*/  sd_uid; int /*<<< orphan*/  sd_ino; int /*<<< orphan*/  sd_dev; TYPE_4__ sd_mtime; TYPE_2__ sd_ctime; } ;
struct cache_entry {short ce_flags; TYPE_6__ oid; TYPE_5__ ce_stat_data; int /*<<< orphan*/  ce_mode; } ;
struct TYPE_14__ {unsigned int rawsz; } ;

/* Variables and functions */
 int CE_EXTENDED ; 
 int CE_EXTENDED_FLAGS ; 
 short CE_NAMEMASK ; 
 short ce_namelen (struct cache_entry*) ; 
 int /*<<< orphan*/  hashcpy (scalar_t__,int /*<<< orphan*/ ) ; 
 void* htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int) ; 
 TYPE_7__* the_hash_algo ; 

__attribute__((used)) static void copy_cache_entry_to_ondisk(struct ondisk_cache_entry *ondisk,
				       struct cache_entry *ce)
{
	short flags;
	const unsigned hashsz = the_hash_algo->rawsz;
	uint16_t *flagsp = (uint16_t *)(ondisk->data + hashsz);

	ondisk->ctime.sec = htonl(ce->ce_stat_data.sd_ctime.sec);
	ondisk->mtime.sec = htonl(ce->ce_stat_data.sd_mtime.sec);
	ondisk->ctime.nsec = htonl(ce->ce_stat_data.sd_ctime.nsec);
	ondisk->mtime.nsec = htonl(ce->ce_stat_data.sd_mtime.nsec);
	ondisk->dev  = htonl(ce->ce_stat_data.sd_dev);
	ondisk->ino  = htonl(ce->ce_stat_data.sd_ino);
	ondisk->mode = htonl(ce->ce_mode);
	ondisk->uid  = htonl(ce->ce_stat_data.sd_uid);
	ondisk->gid  = htonl(ce->ce_stat_data.sd_gid);
	ondisk->size = htonl(ce->ce_stat_data.sd_size);
	hashcpy(ondisk->data, ce->oid.hash);

	flags = ce->ce_flags & ~CE_NAMEMASK;
	flags |= (ce_namelen(ce) >= CE_NAMEMASK ? CE_NAMEMASK : ce_namelen(ce));
	flagsp[0] = htons(flags);
	if (ce->ce_flags & CE_EXTENDED) {
		flagsp[1] = htons((ce->ce_flags & CE_EXTENDED_FLAGS) >> 16);
	}
}