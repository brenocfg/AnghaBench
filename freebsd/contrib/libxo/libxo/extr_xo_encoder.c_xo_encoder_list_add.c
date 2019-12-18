#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * xe_name; } ;
typedef  TYPE_1__ xo_encoder_node_t ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,char const*,int) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  xe_link ; 
 int /*<<< orphan*/  xo_encoders ; 
 int /*<<< orphan*/  xo_free (TYPE_1__*) ; 
 void* xo_realloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static xo_encoder_node_t *
xo_encoder_list_add (const char *name)
{
    if (name == NULL)
	return NULL;

    xo_encoder_node_t *xep = xo_realloc(NULL, sizeof(*xep));
    if (xep) {
	ssize_t len = strlen(name) + 1;
	xep->xe_name = xo_realloc(NULL, len);
	if (xep->xe_name == NULL) {
	    xo_free(xep);
	    return NULL;
	}

	memcpy(xep->xe_name, name, len);

	TAILQ_INSERT_TAIL(&xo_encoders, xep, xe_link);
    }

    return xep;
}