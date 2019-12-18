#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xo_handle_t ;
struct TYPE_6__ {int /*<<< orphan*/  c_data; } ;
typedef  TYPE_1__ cbor_private_t ;

/* Variables and functions */
 int CBOR_INDEF ; 
 int CBOR_MAP ; 
 int /*<<< orphan*/  bzero (TYPE_1__*,int) ; 
 int /*<<< orphan*/  cbor_append (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xo_buf_init (int /*<<< orphan*/ *) ; 
 TYPE_1__* xo_realloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  xo_set_private (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static int
cbor_create (xo_handle_t *xop)
{
    cbor_private_t *cbor = xo_realloc(NULL, sizeof(*cbor));
    if (cbor == NULL)
	return -1;

    bzero(cbor, sizeof(*cbor));
    xo_buf_init(&cbor->c_data);

    xo_set_private(xop, cbor);

    cbor_append(xop, cbor, &cbor->c_data, CBOR_MAP | CBOR_INDEF, 0, NULL);

    return 0;
}