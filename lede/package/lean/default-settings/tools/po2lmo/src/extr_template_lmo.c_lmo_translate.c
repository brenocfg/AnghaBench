#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_6__ {int /*<<< orphan*/  length; int /*<<< orphan*/  offset; } ;
typedef  TYPE_1__ lmo_entry_t ;
struct TYPE_7__ {char* mmap; struct TYPE_7__* next; } ;
typedef  TYPE_2__ lmo_archive_t ;
struct TYPE_8__ {TYPE_2__* archives; } ;

/* Variables and functions */
 TYPE_5__* _lmo_active_catalog ; 
 int /*<<< orphan*/  lmo_canon_hash (char const*,int) ; 
 TYPE_1__* lmo_find_entry (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int ntohl (int /*<<< orphan*/ ) ; 

int lmo_translate(const char *key, int keylen, char **out, int *outlen)
{
	uint32_t hash;
	lmo_entry_t *e;
	lmo_archive_t *ar;

	if (!key || !_lmo_active_catalog)
		return -2;

	hash = lmo_canon_hash(key, keylen);

	for (ar = _lmo_active_catalog->archives; ar; ar = ar->next)
	{
		if ((e = lmo_find_entry(ar, hash)) != NULL)
		{
			*out = ar->mmap + ntohl(e->offset);
			*outlen = ntohl(e->length);
			return 0;
		}
	}

	return -1;
}