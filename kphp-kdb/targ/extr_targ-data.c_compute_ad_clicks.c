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
struct advert {int l_clicked; } ;

/* Variables and functions */
 struct advert* get_ad_f (int,int /*<<< orphan*/ ) ; 

int compute_ad_clicks (int ad_id) {
  struct advert *A = get_ad_f (ad_id, 0);
  return A ? A->l_clicked : 0;
}