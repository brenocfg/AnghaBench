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
typedef  int pgprotval_t ;
typedef  int /*<<< orphan*/  pgprot_t ;

/* Variables and functions */
 int pgprot_val (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool conflicts(pgprot_t prot, pgprotval_t val)
{
	return (pgprot_val(prot) & ~val) != pgprot_val(prot);
}