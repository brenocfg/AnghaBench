#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_9__ ;
typedef  struct TYPE_12__   TYPE_8__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  item_id; } ;
typedef  TYPE_1__ item_t ;
struct TYPE_13__ {int weight; int /*<<< orphan*/  p; } ;
struct TYPE_12__ {int p; int weight; } ;
struct TYPE_11__ {double weight; double (* f ) (TYPE_1__*,TYPE_3__*) ;} ;

/* Variables and functions */
 int FLAG_ONLY_TITLE_SEARCH ; 
 TYPE_9__ QRP ; 
 TYPE_8__ QRT ; 
 int QRT_min_creation_time ; 
 TYPE_3__* QRW ; 
 double Q_K_Opt_Tag ; 
 int /*<<< orphan*/  Q_Relevance_Power ; 
 scalar_t__ Q_optional_tags ; 
 int Q_order ; 
 scalar_t__ Q_relevance ; 
 int RELEVANCE_TABLE_SIZE ; 
 double exp (int) ; 
 void* get_rate_item_fast (TYPE_1__*,int) ; 
 double item_count_optional_tags_sum (TYPE_1__*) ; 
 int now ; 
 double optional_tags_mult_coeff ; 
 double pow (int,int /*<<< orphan*/ ) ; 
 int query_rate_weights ; 
 double stub1 (TYPE_1__*,TYPE_3__*) ; 
 double* tbl_relevance ; 
 int /*<<< orphan*/  vkprintf (int,char*,double,...) ; 

__attribute__((used)) static int evaluate_relevance_search_rating (item_t *I, int priority) {
  int i;
  double r;
  if (!query_rate_weights) { r = 0.5; }
  else {
    r = 0.0;
    i = 0;
    do {
      r += QRW[i].weight * QRW[i].f (I, &QRW[i]);
    } while (++i < query_rate_weights);
  }

  if (!QRP.p) {
    r += QRP.weight * priority;
  }

  if (!(QRT.p & -16)) {
    int rate = get_rate_item_fast (I, QRT.p);
    if (rate < QRT_min_creation_time) {
      return 0;
    }
    if (rate < now) {
      r *= exp (QRT.weight * (now - rate));
    }
  }

  if (r < 0) {
    vkprintf (3, "evaluate_searchx_rating: r = %.lg\n", r);
    return 0;
  }

  if (r > 1) {
    vkprintf (3, "evaluate_searchx_rating: r = %.lg\n", r);
    return 0x7fffffff;
  }

  if (Q_optional_tags) {
    r *= (1.0 + Q_K_Opt_Tag * item_count_optional_tags_sum (I)) * optional_tags_mult_coeff;
  }

  if (Q_relevance) {
    unsigned w = get_rate_item_fast (I, 13);
    vkprintf (3, "item_id = %lld, in title = %d, whole = %d\n", I->item_id, w >> 16, w & 0xffff);
    int l = (Q_order & FLAG_ONLY_TITLE_SEARCH) ? (w >> 16) : (w & 0xffff);
    l++;
    if (l >= RELEVANCE_TABLE_SIZE) { l = RELEVANCE_TABLE_SIZE - 1; }
    if (tbl_relevance[l] < -0.5) {
      tbl_relevance[l] = 1.0 / pow (l, Q_Relevance_Power);
    }
    r *= tbl_relevance[l];
  }

  vkprintf (3, "item_id = %lld, r = %.10lf\n", I->item_id, r);
  return (int) (r * 2147483647.0);
}