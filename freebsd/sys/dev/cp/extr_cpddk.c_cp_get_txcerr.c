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
struct TYPE_3__ {int f; int /*<<< orphan*/  l81; int /*<<< orphan*/  d; } ;
typedef  TYPE_1__ e ;

/* Variables and functions */
 int u (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int cp_get_txcerr(e*a){{if(!(a->f!=1))goto l296;return 0;l296:;}
return(u(a->d,a->l81)&16)!=0;}