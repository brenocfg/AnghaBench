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
struct ablkcipher_walk {int /*<<< orphan*/  out; int /*<<< orphan*/  in; } ;

/* Variables and functions */
 int /*<<< orphan*/  scatterwalk_advance (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static inline void ablkcipher_done_fast(struct ablkcipher_walk *walk,
					unsigned int n)
{
	scatterwalk_advance(&walk->in, n);
	scatterwalk_advance(&walk->out, n);
}