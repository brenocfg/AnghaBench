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
struct mly_softc {int dummy; } ;
struct mly_command {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  debug_called (int) ; 
 struct mly_command* mly_dequeue_free (struct mly_softc*) ; 

__attribute__((used)) static int
mly_alloc_command(struct mly_softc *sc, struct mly_command **mcp)
{
    struct mly_command	*mc;

    debug_called(3);

    if ((mc = mly_dequeue_free(sc)) == NULL)
	return(ENOMEM);

    *mcp = mc;
    return(0);
}