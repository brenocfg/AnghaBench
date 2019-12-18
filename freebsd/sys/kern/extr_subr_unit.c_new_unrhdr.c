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
struct unrhdr {int dummy; } ;
struct mtx {int dummy; } ;

/* Variables and functions */
 struct unrhdr* Malloc (int) ; 
 int /*<<< orphan*/  init_unrhdr (struct unrhdr*,int,int,struct mtx*) ; 

struct unrhdr *
new_unrhdr(int low, int high, struct mtx *mutex)
{
	struct unrhdr *uh;

	uh = Malloc(sizeof *uh);
	init_unrhdr(uh, low, high, mutex);
	return (uh);
}