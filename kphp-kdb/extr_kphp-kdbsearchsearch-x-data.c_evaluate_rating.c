#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct item {double sum_sqr_freq_title; double sum_freq_title_freq_text; double sum_sqr_freq_text; } ;
struct TYPE_3__ {double weight; double (* f ) (struct item*,TYPE_1__*) ;} ;

/* Variables and functions */
 TYPE_1__* QRW ; 
 int query_rate_weights ; 
 double sqr_word_text_weight ; 
 double sqr_word_title_weight ; 
 double sqrt (double) ; 
 double stub1 (struct item*,TYPE_1__*) ; 
 double word_title_weight_word_text_weight ; 

__attribute__((used)) static inline double evaluate_rating (struct item *I, double w) {
  int i;
  //vkprintf (4, "evaluate_rating (itemid = %lld, I->freq_title = %d, I->freq_text = %d\n", I->item_id, (int) I->freq_title, (int) I->freq_text);
  double s = sqr_word_title_weight * I->sum_sqr_freq_title +
             word_title_weight_word_text_weight * I->sum_freq_title_freq_text +
             sqr_word_text_weight * I->sum_sqr_freq_text;
  if (s < 1e-9) { return 1.0; }
  w /= sqrt (s);
  double r = 1.0 - w * QRW[0].weight;
  for (i = 1; i < query_rate_weights; i++) {
    r -= QRW[i].f (I, QRW + i) * QRW[i].weight;
  }
  if (r < 0.0) { r = 0.0; }
  if (r > 1.0) { r = 1.0; }
  return r;
}