#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct metafile {scalar_t__ data; TYPE_1__* header; scalar_t__ aio; } ;
struct index_entry {int /*<<< orphan*/  key_len; int /*<<< orphan*/  data; } ;
struct TYPE_2__ {int nrecords; int /*<<< orphan*/  key_len; int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  debug_dump_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 struct index_entry index_entry_not_found ; 
 int /*<<< orphan*/  load_metafile (int) ; 
 struct index_entry* metafile_get_entry (int,int) ; 
 int metafile_number ; 
 struct metafile* metafiles ; 
 int /*<<< orphan*/  metafiles_cache_miss ; 
 int /*<<< orphan*/  metafiles_cache_ok ; 
 scalar_t__ min (int,int) ; 
 int mystrcmp2 (char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  renew_use (int) ; 
 int /*<<< orphan*/  stderr ; 
 int verbosity ; 

struct index_entry* index_get_next (const char *key, int key_len) {
  int l = -1;
  int r = metafile_number;
  int lc = 1;
  int rc = 1;
  while (r - l > 1) {
    int x = (r + l) >> 1;
    int c = mystrcmp2 (key, key_len, metafiles[x].header->key, metafiles[x].header->key_len, min (lc, rc) - 1);
    if (c < 0) {
      r = x;
      rc = -c;
    } else if (c > 0) {
      l = x;
      lc = c;
    } else {
      l = x;
      break;
    }
  }
  if (l < 0) { l = 0; }
  if (l >= metafile_number) {
    if (verbosity >= 4) { fprintf (stderr, "not found[1]\n"); }
    return &index_entry_not_found;
  }
  if (verbosity >= 4) {
    fprintf (stderr, "(l,r) = (%d,%d)\n", l, r);
  }
  int ll = l;
  int ll_start = ll;
  while (1) {
    assert (ll_start - ll < 2);
    if (ll == metafile_number) {
      return &index_entry_not_found;
    }
    if (metafiles[ll].data == 0 || metafiles[ll].aio) {
      load_metafile (ll);
	    if (metafiles[ll].data == 0 || metafiles[ll].aio) {
        metafiles_cache_miss ++;
    	  return 0;
    	}
    }
    metafiles_cache_ok ++;
    renew_use (ll);
    int metafile = ll;
    struct metafile* meta = &metafiles[ll];

    l = -1;
    r = meta->header->nrecords;
    lc = 1;
    rc = 1;
    while (r-l > 1) {
      int x = (r+l)>>1;
      int c = mystrcmp2 (key, key_len, metafile_get_entry (metafile, x)->data, metafile_get_entry (metafile, x)->key_len, min (lc, rc) - 1); 
      if (c < 0) {
        r = x;
        rc = -c;
      } else if (c > 0) {
        l = x;
        lc = c;
      } else {
        l = x; 
        break;
      }
    }
    if (verbosity>=4) {
      fprintf (stderr, "(l,r) = (%d,%d)\n", l, r);
    }
    l ++;

    if (l == meta->header->nrecords) {
      ll ++;
      continue;
    }
  
    struct index_entry *E = metafile_get_entry (metafile, l);
    if (verbosity >= 4) {
      fprintf (stderr, "metafile_get_entry (%d, %d)->key = ", metafile, l);
      debug_dump_key (E->data, E->key_len);
    }
    return metafile_get_entry (metafile, l);
  }
}