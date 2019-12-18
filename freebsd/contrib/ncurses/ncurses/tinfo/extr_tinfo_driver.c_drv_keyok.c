#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  _key_ok; int /*<<< orphan*/  _keytry; } ;
typedef  int /*<<< orphan*/  TERMINAL_CONTROL_BLOCK ;
typedef  TYPE_1__ SCREEN ;

/* Variables and functions */
 int /*<<< orphan*/  AssertTCB () ; 
 int ERR ; 
 int OK ; 
 int /*<<< orphan*/  SetSP () ; 
 int _nc_add_to_try (int /*<<< orphan*/ *,char*,unsigned int) ; 
 char* _nc_expand_try (int /*<<< orphan*/ ,unsigned int,int*,size_t) ; 
 scalar_t__ _nc_remove_key (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  free (char*) ; 

__attribute__((used)) static int
drv_keyok(TERMINAL_CONTROL_BLOCK * TCB, int c, int flag)
{
    SCREEN *sp;
    int code = ERR;
    int count = 0;
    char *s;

    AssertTCB();
    SetSP();

    if (c >= 0) {
	unsigned ch = (unsigned) c;
	if (flag) {
	    while ((s = _nc_expand_try(sp->_key_ok,
				       ch, &count, (size_t) 0)) != 0
		   && _nc_remove_key(&(sp->_key_ok), ch)) {
		code = _nc_add_to_try(&(sp->_keytry), s, ch);
		free(s);
		count = 0;
		if (code != OK)
		    break;
	    }
	} else {
	    while ((s = _nc_expand_try(sp->_keytry,
				       ch, &count, (size_t) 0)) != 0
		   && _nc_remove_key(&(sp->_keytry), ch)) {
		code = _nc_add_to_try(&(sp->_key_ok), s, ch);
		free(s);
		count = 0;
		if (code != OK)
		    break;
	    }
	}
    }
    return (code);
}