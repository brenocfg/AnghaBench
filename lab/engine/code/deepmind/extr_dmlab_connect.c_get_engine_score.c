#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {double* persistant; } ;
struct TYPE_5__ {TYPE_1__ ps; } ;
struct TYPE_6__ {TYPE_2__ snap; } ;

/* Variables and functions */
 size_t PERS_SCORE ; 
 TYPE_3__ cl ; 

__attribute__((used)) static double get_engine_score(void) {
  return cl.snap.ps.persistant[PERS_SCORE];
}