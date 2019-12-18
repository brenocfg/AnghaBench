#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  rating ;
struct TYPE_4__ {long long x; scalar_t__ y; } ;
typedef  TYPE_1__ hmap_pair_ll_int ;
struct TYPE_5__ {int y; } ;

/* Variables and functions */
 scalar_t__ H_ADD ; 
 long long H_MUL ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int* dl_realloc (int*,int,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  h_id ; 
 TYPE_2__* hmap_ll_int_add (int /*<<< orphan*/ *,TYPE_1__) ; 
 int idn ; 
 int idr ; 
 int* names ; 
 int* names_buff ; 
 int namesn ; 
 int namesr ; 
 int* ratings ; 
 int /*<<< orphan*/  stderr ; 
 int stem_str (char*) ; 
 int* stemmed_names ; 
 int /*<<< orphan*/  strcpy (int*,char*) ; 
 int strlen (char*) ; 
 scalar_t__ use_stemmer ; 

int add_id (char *s, int *v, int debug) {
  long long h = 0;
  int i;
  for (i = 0; v[i]; i++) {
    h = h * H_MUL + v[i];
  }

  h += H_ADD;
  hmap_pair_ll_int tmp;
  tmp.x = h;
  tmp.y = 0;
  int *pid = &(hmap_ll_int_add (&h_id, tmp)->y);

  if (idn + 3 > idr) {
    int nidr = idr * 2 + 3;
    names = dl_realloc (names, sizeof (int) * nidr, sizeof (int) * idr);
    stemmed_names = dl_realloc (stemmed_names, sizeof (int) * nidr, sizeof (int) * idr);
    ratings = dl_realloc (ratings, sizeof (rating) * nidr, sizeof (rating) * idr);
    ratings[0] = 0;
    idr = nidr;

    assert (names != NULL);
    assert (stemmed_names != NULL);
    assert (ratings != NULL);
  }

  if (*pid == 0) {
    *pid = ++idn;

    int sn = strlen (s);
    if (namesn + sn + 3 > namesr) {
      int nnamesr = namesr * 2 + sn + 3;
      names_buff = dl_realloc (names_buff, sizeof (char) * nnamesr, sizeof (char) * namesr);
      namesr = nnamesr;

      assert (names_buff != NULL);
    }

    names[idn] = namesn;
    if (use_stemmer) {
      stemmed_names[idn] = stem_str (s);
    } else {
      stemmed_names[idn] = idn;
    }
    if (debug) {
      fprintf (stderr, "<%s>\n", s);
    }

    strcpy (names_buff + namesn, s);
    namesn += sn + 1;
    ratings[idn] = 0;
  }

  return *pid;
}