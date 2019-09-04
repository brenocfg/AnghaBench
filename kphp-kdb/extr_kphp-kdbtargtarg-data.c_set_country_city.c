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
struct TYPE_3__ {int uni_country; int uni_city; int /*<<< orphan*/  uid; } ;
typedef  TYPE_1__ user_t ;
struct lev_univcity {int uni_country; int uni_city; int /*<<< orphan*/  user_id; } ;

/* Variables and functions */
 TYPE_1__* get_user (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  q_city ; 
 int /*<<< orphan*/  q_country ; 
 int /*<<< orphan*/  user_change_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

void set_country_city (struct lev_univcity *E) {
  user_t *U = get_user (E->user_id);
  if (U && E->uni_country >= 0 && E->uni_country <= 255 && E->uni_city >= 0) { 
    user_change_field (U->uid, q_country, U->uni_country, E->uni_country);
    user_change_field (U->uid, q_city, U->uni_city, E->uni_city);
    U->uni_country = E->uni_country;
    U->uni_city = E->uni_city;
  }
}