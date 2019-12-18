#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int v_type; char* v_value; int /*<<< orphan*/  v_access; } ;
typedef  TYPE_1__ value_t ;

/* Variables and functions */
#define  BOOL 131 
 int /*<<< orphan*/  CHANGED ; 
#define  CHAR 130 
 int ENVIRON ; 
 int INIT ; 
 char* NOSTR ; 
#define  NUMBER 129 
#define  STRING 128 
 int TMASK ; 
 int /*<<< orphan*/  WRITE ; 
 int boolean (char*) ; 
 char character (char*) ; 
 int /*<<< orphan*/  equal (char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  number (char*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  setboolean (char*,int) ; 
 int /*<<< orphan*/  setcharacter (char*,char) ; 
 int /*<<< orphan*/  setnumber (char*,int /*<<< orphan*/ ) ; 
 char* strdup (char*) ; 
 int /*<<< orphan*/  vaccess (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vassign(value_t *p, char *v)
{
	if (!vaccess(p->v_access, WRITE)) {
		printf("access denied\r\n");
		return;
	}

	switch (p->v_type&TMASK) {
	case STRING:
		if (p->v_value && equal(p->v_value, v))
			return;
		if (!(p->v_type&(ENVIRON|INIT)))
			free(p->v_value);
		if ((p->v_value = strdup(v)) == NOSTR) {
			printf("out of core\r\n");
			return;
		}
		p->v_type &= ~(ENVIRON|INIT);
		break;
	case NUMBER:
		if (number(p->v_value) == number(v))
			return;
		setnumber(p->v_value, number(v));
		break;
	case BOOL:
		if (boolean(p->v_value) == (*v != '!'))
			return;
		setboolean(p->v_value, (*v != '!'));
		break;
	case CHAR:
		if (character(p->v_value) == *v)
			return;
		setcharacter(p->v_value, *v);
	}
	p->v_access |= CHANGED;
}