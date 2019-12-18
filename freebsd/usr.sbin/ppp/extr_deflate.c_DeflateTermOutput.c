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
struct deflate_state {int /*<<< orphan*/  cx; } ;

/* Variables and functions */
 int /*<<< orphan*/  deflateEnd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct deflate_state*) ; 

__attribute__((used)) static void
DeflateTermOutput(void *v)
{
  struct deflate_state *state = (struct deflate_state *)v;

  deflateEnd(&state->cx);
  free(state);
}