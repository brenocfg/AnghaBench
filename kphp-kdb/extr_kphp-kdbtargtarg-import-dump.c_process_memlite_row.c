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
struct lev_birthday {int user_id; int day; int month; int year; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int* I ; 
 int* L ; 
 int /*<<< orphan*/  LEV_TARG_BIRTHDAY ; 
 int /*<<< orphan*/  LEV_TARG_CUTE ; 
 int /*<<< orphan*/  LEV_TARG_MSTATUS ; 
 int /*<<< orphan*/  LEV_TARG_ONLINE ; 
 int /*<<< orphan*/  LEV_TARG_POLITICAL ; 
 int /*<<< orphan*/  LEV_TARG_PRIVACY ; 
 int /*<<< orphan*/  LEV_TARG_RATE ; 
 int /*<<< orphan*/  LEV_TARG_RATECUTE ; 
 int /*<<< orphan*/  LEV_TARG_SEX ; 
 int /*<<< orphan*/  LEV_TARG_UNIVCITY ; 
 scalar_t__ LEV_TARG_USERFLAGS ; 
 int /*<<< orphan*/  adj_rec ; 
 int /*<<< orphan*/  fits (int) ; 
 int /*<<< orphan*/  log_0ints (scalar_t__) ; 
 int /*<<< orphan*/  log_1int (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  log_2ints (int /*<<< orphan*/ ,int,int) ; 
 size_t ml_bday_day ; 
 size_t ml_bday_month ; 
 size_t ml_bday_year ; 
 size_t ml_cute ; 
 size_t ml_id ; 
 size_t ml_ip ; 
 size_t ml_logged ; 
 size_t ml_photo ; 
 size_t ml_political ; 
 size_t ml_profile_privacy ; 
 size_t ml_rate ; 
 size_t ml_sex ; 
 size_t ml_status ; 
 size_t ml_uni_city ; 
 size_t ml_uni_country ; 
 int user_id ; 
 struct lev_birthday* write_alloc (int) ; 

void process_memlite_row (void) {
  struct lev_birthday *LB;

  if (!fits(I[ml_id])) {
    return;
  }

  user_id = I[ml_id];

  if (I[ml_bday_day] || I[ml_bday_month] || I[ml_bday_year]) {
    LB = write_alloc (sizeof (struct lev_birthday));
    LB->type = LEV_TARG_BIRTHDAY;
    LB->user_id = I[ml_id];
    LB->day = I[ml_bday_day];
    LB->month = I[ml_bday_month];
    LB->year = I[ml_bday_year];
  }

  if (I[ml_uni_country] || I[ml_uni_city]) {
    log_2ints (LEV_TARG_UNIVCITY, I[ml_uni_country], I[ml_uni_city]);
  }

  if (I[ml_ip] || I[ml_logged]) {
    log_2ints (LEV_TARG_ONLINE, I[ml_ip], I[ml_logged]);
  }

  if (I[ml_sex]) {
    log_1int (LEV_TARG_SEX, I[ml_sex]);
  }

  if (I[ml_political]) {
    log_1int (LEV_TARG_POLITICAL, I[ml_political]);
  }

  if (I[ml_rate]) {
    if (I[ml_cute]) {
      log_2ints (LEV_TARG_RATECUTE, I[ml_rate], I[ml_cute]);
    } else {
      log_1int (LEV_TARG_RATE, I[ml_rate]);
    }
  } else if (I[ml_cute]) {
    log_1int (LEV_TARG_CUTE, I[ml_cute]);
  }

  if (I[ml_profile_privacy] != 1) {
    log_1int (LEV_TARG_PRIVACY, I[ml_profile_privacy]);
  }

  if (I[ml_status]) {
    log_1int (LEV_TARG_MSTATUS, I[ml_status]);
  }

  if (L[ml_photo] > 4) {
    log_0ints (LEV_TARG_USERFLAGS + 1);
  }

  adj_rec++;

}