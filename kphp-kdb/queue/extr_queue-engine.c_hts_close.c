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
struct hts_data {TYPE_2__* extra; } ;
struct connection {int dummy; } ;
struct TYPE_5__ {int n; TYPE_1__** k; } ;
typedef  TYPE_2__ qkey_group ;
struct TYPE_4__ {scalar_t__ lock; int /*<<< orphan*/ * conn; scalar_t__ subscribed; } ;

/* Variables and functions */
 struct hts_data* HTS_DATA (struct connection*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  qkey_group_free (TYPE_2__*) ; 

int hts_close (struct connection *c, int who) {
  struct hts_data *D = HTS_DATA(c);

  qkey_group *k = D->extra;

  if (k != NULL) {
    int i;
    for (i = 0; i < k->n; i++) {
      k->k[i]->lock--;
      k->k[i]->subscribed = 0;
      k->k[i]->conn = NULL;
      assert (k->k[i]->lock >= 0);
    }
    qkey_group_free (k);
    D->extra = NULL;
  }


  return 0;
}