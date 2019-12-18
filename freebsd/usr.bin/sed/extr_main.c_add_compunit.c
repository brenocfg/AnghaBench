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
struct s_compunit {int type; char* s; struct s_compunit* next; } ;
typedef  enum e_cut { ____Placeholder_e_cut } e_cut ;

/* Variables and functions */
 struct s_compunit** cu_nextp ; 
 int /*<<< orphan*/  err (int,char*) ; 
 struct s_compunit* malloc (int) ; 

__attribute__((used)) static void
add_compunit(enum e_cut type, char *s)
{
	struct s_compunit *cu;

	if ((cu = malloc(sizeof(struct s_compunit))) == NULL)
		err(1, "malloc");
	cu->type = type;
	cu->s = s;
	cu->next = NULL;
	*cu_nextp = cu;
	cu_nextp = &cu->next;
}