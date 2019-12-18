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
struct iwdp_ipage_struct {int dummy; } ;
typedef  scalar_t__ iwdp_ipage_t ;

/* Variables and functions */
 int /*<<< orphan*/  malloc (int) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int) ; 

iwdp_ipage_t iwdp_ipage_new() {
  iwdp_ipage_t ipage = (iwdp_ipage_t)malloc(sizeof(struct iwdp_ipage_struct));
  if (ipage) {
    memset(ipage, 0, sizeof(struct iwdp_ipage_struct));
  }
  return ipage;
}