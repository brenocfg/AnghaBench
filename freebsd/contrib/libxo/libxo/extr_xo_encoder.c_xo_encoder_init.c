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
typedef  int /*<<< orphan*/  xo_handle_t ;
struct TYPE_4__ {int /*<<< orphan*/  xe_handler; } ;
typedef  TYPE_1__ xo_encoder_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  XO_OP_CREATE ; 
 int /*<<< orphan*/  XO_OP_OPTIONS ; 
 char* alloca (size_t) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 char* strchr (char const*,char) ; 
 size_t strlen (char const*) ; 
 TYPE_1__* xo_encoder_discover (char const*) ; 
 TYPE_1__* xo_encoder_find (char const*) ; 
 int xo_encoder_handle (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xo_encoder_setup () ; 
 int /*<<< orphan*/  xo_failure (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  xo_set_encoder (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
xo_encoder_init (xo_handle_t *xop, const char *name)
{
    xo_encoder_setup();

    const char *opts = strchr(name, ':');
    if (opts) {
	/* Make a writable copy of the name */
	size_t len = strlen(name);
	char *copy = alloca(len + 1);
	memcpy(copy, name, len);
	copy[len] = '\0';

	char *opts_copy = copy + (opts - name); /* Move to ':' */
	*opts_copy++ = '\0';			/* Trim it off */

	opts = opts_copy;	/* Use copy as options */
	name = copy;		/* Use trimmed copy as name */
    }

    /* Can't have names containing '/' or ':' */
    if (strchr(name, '/') != NULL || strchr(name, ':') != NULL) {
	xo_failure(xop, "invalid encoder name: %s", name);
	return -1;
    }

   /*
     * First we look on the list of known (registered) encoders.
     * If we don't find it, we follow the set of paths to find
     * the encoding library.
     */
    xo_encoder_node_t *xep = xo_encoder_find(name);
    if (xep == NULL) {
	xep = xo_encoder_discover(name);
	if (xep == NULL) {
	    xo_failure(xop, "encoder not founde: %s", name);
	    return -1;
	}
    }

    xo_set_encoder(xop, xep->xe_handler);

    int rc = xo_encoder_handle(xop, XO_OP_CREATE, name, NULL, 0);
    if (rc == 0 && opts != NULL) {
	rc = xo_encoder_handle(xop, XO_OP_OPTIONS, name, opts, 0);
    }

    return rc;
}