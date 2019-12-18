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
typedef  size_t* data ;

/* Variables and functions */
 int MAXQ ; 
 scalar_t__ RATING_MIN ; 
 int /*<<< orphan*/  black_list_check (scalar_t__) ; 
 float get_rating (size_t) ; 
 scalar_t__* names ; 
 scalar_t__ names_buff ; 
 size_t* q ; 
 float* rating_q ; 
 scalar_t__* ratings ; 
 scalar_t__* stemmed_names ; 
 int /*<<< orphan*/  swap (size_t,size_t) ; 

void merge (data p) {
  int ip, iq;

  for (ip = 0; ip < MAXQ && ratings[p[ip]] > RATING_MIN; ip++) {
    if (!black_list_check (names_buff + names[p[ip]])) {
//      fprintf (stderr, "<%s>\n", names_buff + names[p[ip]]);
      float rb = get_rating (p[ip]);

      for (iq = 0; iq < MAXQ; iq++)
        if (stemmed_names[q[iq]] == stemmed_names[p[ip]]) {
          if (rb > rating_q[iq]) {
            rating_q[iq] = rb;

            while (iq > 0 && rating_q[iq - 1] < rating_q[iq]) {
              swap (rating_q[iq - 1], rating_q[iq]);
              swap (q[iq - 1], q[iq]);
            }
          }

          break;
        }

      if (iq == MAXQ) {
        if (rating_q[MAXQ - 1] < rb) {
          int i;
          for (i = MAXQ - 2; i >= 0 && rating_q[i] < rb; i--) {
            q[i + 1] = q[i];
            rating_q[i + 1] = rating_q[i];
          }
          q[i + 1] = p[ip];
          rating_q[i + 1] = rb;
        }
      }
    }
  }
}