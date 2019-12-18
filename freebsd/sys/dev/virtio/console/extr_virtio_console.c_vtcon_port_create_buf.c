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
struct vtcon_port {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_NOWAIT ; 
 int M_ZERO ; 
 int /*<<< orphan*/  VTCON_BULK_BUFSZ ; 
 int /*<<< orphan*/  free (void*,int /*<<< orphan*/ ) ; 
 void* malloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int vtcon_port_enqueue_buf (struct vtcon_port*,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
vtcon_port_create_buf(struct vtcon_port *port)
{
	void *buf;
	int error;

	buf = malloc(VTCON_BULK_BUFSZ, M_DEVBUF, M_ZERO | M_NOWAIT);
	if (buf == NULL)
		return (ENOMEM);

	error = vtcon_port_enqueue_buf(port, buf, VTCON_BULK_BUFSZ);
	if (error)
		free(buf, M_DEVBUF);

	return (error);
}