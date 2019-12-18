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

/* Variables and functions */
 int INIT_L_VIEWS ; 

__attribute__((used)) static int compute_projected_views (int audience) {
  if (audience <= 0) {
    return INIT_L_VIEWS;
  } else if (audience <= 1000) {
    return INIT_L_VIEWS * 8 / 10;  /* up to 1K users */
  } else if (audience <= 32000) {
    return INIT_L_VIEWS * 9 / 10;  /* 1K..32K users */
  } else if (audience <= 12000000) {
    return INIT_L_VIEWS;           /* 32K..12M users */
  } else if (audience <= 80000000) {
    return INIT_L_VIEWS * 12 / 10; /* 12M..80M users */
  } else {
    return INIT_L_VIEWS * 15 / 10; /* 80M..more spam bots */
  }
}