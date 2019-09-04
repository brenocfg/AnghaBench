#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {long long nbad; long long ngood; } ;
struct TYPE_12__ {scalar_t__ metafile; TYPE_7__ b; } ;
typedef  TYPE_1__ user ;
struct TYPE_13__ {char* text; } ;
typedef  TYPE_2__ message ;
struct TYPE_14__ {char* text; struct TYPE_14__* next; } ;
typedef  TYPE_3__ black_list ;

/* Variables and functions */
 int BAYES_MAX_WORDS ; 
 size_t HAM ; 
 int /*<<< orphan*/  NOAIO ; 
 int QL ; 
 int QR ; 
 size_t SPAM ; 
 double bayes_get_count (TYPE_7__*,scalar_t__,size_t) ; 
 double bayes_local_get_count (scalar_t__,scalar_t__,size_t) ; 
 TYPE_3__* bl_head ; 
 TYPE_1__* conv_uid (int) ; 
 scalar_t__ debug ; 
 char* debug_buff ; 
 int debug_on ; 
 int /*<<< orphan*/  debugp (char*,long long,double,double,double,double,...) ; 
 char* ds ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ get_words (char*) ; 
 TYPE_7__ global_bayes ; 
 int /*<<< orphan*/  load_user_metafile (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int local_uid (int) ; 
 scalar_t__ msg_verify (TYPE_2__*,int) ; 
 int /*<<< orphan*/  my_qsort (double*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sscanf (char*,char*,int*) ; 
 int /*<<< orphan*/  stderr ; 
 char* strstr (char*,char*) ; 
 int /*<<< orphan*/  user_loaded (TYPE_1__*) ; 
 int verbosity ; 
 scalar_t__* words ; 
 double* words_prob ; 

double bayes_is_spam_prob (message *msg, int random_tag) {
  if (msg_verify (msg, random_tag) < 0) {
    return -1;
  }

  if (verbosity > 2) {
    fprintf (stderr, "bayes_is_spam_prob\n%s\n", msg->text);
  }


  black_list *cur = bl_head;
  while (cur->next != NULL && !strstr (msg->text, cur->next->text)) {
    cur = cur->next;
  }

  if (cur->next != NULL) {
    return 1.0;
  }

             	
  long long nbad = global_bayes.nbad, ngood = global_bayes.ngood, all = nbad + ngood;

  if (!nbad || !ngood) {
    return 0.0;
  }

  debug = 0;

  if (debug) {
    debug_on = 1;
    ds = debug_buff;
  }

/*  int out = 0;
  char *out_s = strstr (msg->text, "out ");
  if (out_s != NULL) {
    sscanf (out_s + 5, "%d", &out);
  }

  if (out == 1) {
    return 0.0;
  }*/

  int uid = 0;
  char *uid_s = strstr (msg->text, "uid ");
  if (uid_s != NULL) {
    sscanf (uid_s + 5, "%d", &uid);
  }
  int local_id = local_uid (uid);
  user *u = conv_uid (uid);

  long long nbad_u = 0, ngood_u = 0, all_u = 0;
  double mul_u = 0.0;

  if (u != NULL) {
    load_user_metafile (u, local_id, NOAIO);

    if (!user_loaded (u)) {
      return -2;
    }

    nbad_u = u->b.nbad + ((int *)u->metafile)[SPAM];
    ngood_u = u->b.ngood + ((int *)u->metafile)[HAM];
    all_u = nbad_u + ngood_u;


    if (all_u >= 50 && nbad_u * 1.0 / ngood_u <= 5 * 1.0 * nbad / ngood) {
      mul_u = (double)all / all_u / 10;
    }
  }
//  mul_u = 0;

  if (get_words (msg->text) < 0) {
    return 1.0;
  }

  double p1 = 3.5 * nbad / all, p2 = 1.0 * ngood / all;

  int i;

  if (debug) {
    fprintf (stderr, "mul_u = %.6lf, ngood = %lld, nbad = %lld, ngood_u = %lld, nbad_u = %lld\n", mul_u, ngood, nbad, ngood_u, nbad_u);
  }
  debugp ("mul_u = %.6lf, ngood = %lld, nbad = %lld, ngood_u = %lld, nbad_u = %lld\n", mul_u, ngood, nbad, ngood_u, nbad_u);

  for (i = 0; words[i]; i++) {
    double gcnt = bayes_get_count (&global_bayes, words[i], HAM),
           bcnt = bayes_get_count (&global_bayes, words[i], SPAM),
           total = gcnt + bcnt;

    if (debug) {
      fprintf (stderr, "(%.3lf;%.3lf)%c", gcnt, bcnt, " \n"[!words[i + 1]]);
    }

    if (u != NULL && mul_u > 1e-9) {
      gcnt += mul_u * (ngood_u + 0.0) / (nbad_u + ngood_u + 0) * total / all;
      bcnt += mul_u * (nbad_u + 0.0) / (nbad_u + ngood_u + 0) * total / all;

      gcnt += bayes_get_count (&u->b, words[i], HAM) * mul_u,
      bcnt += bayes_get_count (&u->b, words[i], SPAM) * mul_u,

      gcnt += bayes_local_get_count (u->metafile + 2 * sizeof (int), words[i], HAM) * mul_u;
      bcnt += bayes_local_get_count (u->metafile + 2 * sizeof (int), words[i], SPAM) * mul_u;
    }

    if (debug) {
      fprintf (stderr, "(%.3lf;%.3lf)%c", gcnt, bcnt, " \n"[!words[i + 1]]);
    }


    double g = p1 * (gcnt + (ngood + 1.0) / (nbad + ngood + 1) );
    double b = p2 * (bcnt + (nbad + 1.0) / (nbad + ngood + 1) );

    if (debug) {
      fprintf (stderr, "(%.3lf;%.3lf)%c", g, b, " \n"[!words[i + 1]]);
    }

    words_prob[i] = b / (g + b);

    if (words_prob[i] < 0.01) {
      words_prob[i] = 0.01;
    }

    if (words_prob[i] > 0.99) {
      words_prob[i] = 0.99;
    }

    debugp ("%lld : %.7lf     (%.3lf+%lf;%.3lf+%lf)\n", (long long)words[i], words_prob[i], g, gcnt, b, bcnt);
  }

  int wn = i;

  QL = BAYES_MAX_WORDS - 1;
  QR = wn - BAYES_MAX_WORDS;

  my_qsort (words_prob, 0, wn - 1);

  if (debug) {
    for (i = 0; i < wn; i++) {
      fprintf (stderr, "%.3lf%c", words_prob[i], " \n"[i + 1 == wn]);
    }
  }

  int res_cnt = BAYES_MAX_WORDS;
  int l = 0, r = wn - 1;
  p1 = 1.0, p2 = 1.0;

  while (res_cnt-- > 0 && l <= r) {
    if (1.0 < words_prob[r] + words_prob[l]) {
       p1 *= words_prob[r];
       p2 *= 1 - words_prob[r--];
    } else {
       p1 *= words_prob[l];
       p2 *= 1 - words_prob[l++];
    }
  }

  if (debug) {
    fprintf (stderr, "RES: %.3lf\n", p1 / (p1 + p2));
  }

  if (debug) {
    fprintf (stderr, "%s\n", debug_buff);
  }

  if (debug) {
    debug_on = 0;
    debug = 0;
  }

  return p1 / (p1 + p2);
}