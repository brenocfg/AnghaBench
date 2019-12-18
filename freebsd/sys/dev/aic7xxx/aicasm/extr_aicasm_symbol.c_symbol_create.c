#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  type; int /*<<< orphan*/ * name; } ;
typedef  TYPE_1__ symbol_t ;

/* Variables and functions */
 int /*<<< orphan*/  EX_SOFTWARE ; 
 int /*<<< orphan*/  UNINITIALIZED ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  stop (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * strdup (char const*) ; 

__attribute__((used)) static symbol_t *
symbol_create(const char *name)
{
	symbol_t *new_symbol;

	new_symbol = (symbol_t *)malloc(sizeof(symbol_t));
	if (new_symbol == NULL) {
		perror("Unable to create new symbol");
		exit(EX_SOFTWARE);
	}
	memset(new_symbol, 0, sizeof(*new_symbol));
	new_symbol->name = strdup(name);
	if (new_symbol->name == NULL)
		 stop("Unable to strdup symbol name", EX_SOFTWARE);
	new_symbol->type = UNINITIALIZED;
	return (new_symbol);
}