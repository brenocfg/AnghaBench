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
struct peer {int dummy; } ;
typedef  unsigned int associd_t ;

/* Variables and functions */
 unsigned int current_association_ID ; 
 struct peer* findpeerbyassoc (unsigned int) ; 
 unsigned int initial_association_ID ; 
 int /*<<< orphan*/  unpeer (struct peer*) ; 

void peer_cleanup(void)
{
        struct peer *peer;
        associd_t assoc;

        for (assoc = initial_association_ID; assoc != current_association_ID; assoc++) {
            if (assoc != 0U) {
                peer = findpeerbyassoc(assoc);
                if (peer != NULL)
                    unpeer(peer);
            }
        }
        peer = findpeerbyassoc(current_association_ID);
        if (peer != NULL)
            unpeer(peer);
}