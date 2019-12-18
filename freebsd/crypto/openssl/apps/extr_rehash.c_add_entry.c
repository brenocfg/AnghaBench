#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  enum Type { ____Placeholder_Type } Type ;
struct TYPE_6__ {int type; unsigned int hash; scalar_t__ num_needed; TYPE_1__* last_entry; TYPE_1__* first_entry; struct TYPE_6__* next; } ;
struct TYPE_5__ {unsigned short old_id; int need_symlink; int /*<<< orphan*/  digest; struct TYPE_5__* next; int /*<<< orphan*/  filename; } ;
typedef  TYPE_1__ HENTRY ;
typedef  TYPE_2__ BUCKET ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char const*,...) ; 
 scalar_t__ MAX_COLLISIONS ; 
 int /*<<< orphan*/  OPENSSL_strdup (char const*) ; 
 int OSSL_NELEM (TYPE_2__**) ; 
 int TYPE_CERT ; 
 void* app_malloc (int,char*) ; 
 int /*<<< orphan*/  bio_err ; 
 int /*<<< orphan*/  evpmdsize ; 
 TYPE_2__** hash_table ; 
 scalar_t__ memcmp (unsigned char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opt_getprog () ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int add_entry(enum Type type, unsigned int hash, const char *filename,
                      const unsigned char *digest, int need_symlink,
                      unsigned short old_id)
{
    static BUCKET nilbucket;
    static HENTRY nilhentry;
    BUCKET *bp;
    HENTRY *ep, *found = NULL;
    unsigned int ndx = (type + hash) % OSSL_NELEM(hash_table);

    for (bp = hash_table[ndx]; bp; bp = bp->next)
        if (bp->type == type && bp->hash == hash)
            break;
    if (bp == NULL) {
        bp = app_malloc(sizeof(*bp), "hash bucket");
        *bp = nilbucket;
        bp->next = hash_table[ndx];
        bp->type = type;
        bp->hash = hash;
        hash_table[ndx] = bp;
    }

    for (ep = bp->first_entry; ep; ep = ep->next) {
        if (digest && memcmp(digest, ep->digest, evpmdsize) == 0) {
            BIO_printf(bio_err,
                       "%s: warning: skipping duplicate %s in %s\n",
                       opt_getprog(),
                       type == TYPE_CERT ? "certificate" : "CRL", filename);
            return 0;
        }
        if (strcmp(filename, ep->filename) == 0) {
            found = ep;
            if (digest == NULL)
                break;
        }
    }
    ep = found;
    if (ep == NULL) {
        if (bp->num_needed >= MAX_COLLISIONS) {
            BIO_printf(bio_err,
                       "%s: error: hash table overflow for %s\n",
                       opt_getprog(), filename);
            return 1;
        }
        ep = app_malloc(sizeof(*ep), "collision bucket");
        *ep = nilhentry;
        ep->old_id = ~0;
        ep->filename = OPENSSL_strdup(filename);
        if (bp->last_entry)
            bp->last_entry->next = ep;
        if (bp->first_entry == NULL)
            bp->first_entry = ep;
        bp->last_entry = ep;
    }

    if (old_id < ep->old_id)
        ep->old_id = old_id;
    if (need_symlink && !ep->need_symlink) {
        ep->need_symlink = 1;
        bp->num_needed++;
        memcpy(ep->digest, digest, evpmdsize);
    }
    return 0;
}