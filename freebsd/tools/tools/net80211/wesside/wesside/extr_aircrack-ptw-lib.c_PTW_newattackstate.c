#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__** table; } ;
struct TYPE_6__ {int b; } ;
typedef  TYPE_2__ PTW_attackstate ;

/* Variables and functions */
 int PTW_KEYHSBYTES ; 
 int /*<<< orphan*/  bzero (TYPE_2__*,int) ; 
 TYPE_2__* malloc (int) ; 
 int n ; 

PTW_attackstate * PTW_newattackstate() {
	int i,k;
	PTW_attackstate * state = NULL;
	state = malloc(sizeof(PTW_attackstate));
	if (state == NULL) {
		return NULL;
	}
	bzero(state, sizeof(PTW_attackstate));
	for (i = 0; i < PTW_KEYHSBYTES; i++) {
                for (k = 0; k < n; k++) {
                        state->table[i][k].b = k;
                }
        }
        return state;
}