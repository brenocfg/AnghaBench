#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* d; int /*<<< orphan*/  l48; } ;
typedef  TYPE_1__ e ;
struct TYPE_6__ {int /*<<< orphan*/  l83; } ;

/* Variables and functions */
 int /*<<< orphan*/  l (TYPE_2__*,int /*<<< orphan*/ ,unsigned char) ; 
 unsigned char u (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned char l57(e*a,unsigned char z){l(a->d,a->l48,z);
return u(a->d,a->d->l83);}