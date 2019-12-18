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
struct open_file {scalar_t__ f_raoffset; scalar_t__ f_ralen; int /*<<< orphan*/  f_rabuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  SOPEN_RASIZE ; 
 int /*<<< orphan*/  malloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
o_rainit(struct open_file *f)
{
	f->f_rabuf = malloc(SOPEN_RASIZE);
	f->f_ralen = 0;
	f->f_raoffset = 0;
}