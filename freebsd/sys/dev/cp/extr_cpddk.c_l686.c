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
struct TYPE_4__ {scalar_t__* j; } ;
struct TYPE_5__ {TYPE_1__ o; } ;
typedef  TYPE_2__ e ;

/* Variables and functions */

__attribute__((used)) static int l686(e*a,int l87){{if(!(a->o.j[l87]))goto l731;{
a->o.j[l87]=0;return 1;}goto l729;l731:;return 0;l729:;}}