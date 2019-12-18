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
struct dcons_softc {int dummy; } ;
struct dcons_buf {int /*<<< orphan*/  magic; int /*<<< orphan*/  version; } ;

/* Variables and functions */
 int DCONS_HEADER_SIZE ; 
 int /*<<< orphan*/  DCONS_MAGIC ; 
 int /*<<< orphan*/  DCONS_VERSION ; 
 int /*<<< orphan*/  dcons_init_port (int,int,int,struct dcons_buf*,struct dcons_softc*) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 

void
dcons_init(struct dcons_buf *buf, int size, struct dcons_softc *sc)
{
	int size0, size1, offset;

	offset = DCONS_HEADER_SIZE;
	size0 = (size - offset);
	size1 = size0 * 3 / 4;		/* console port buffer */

	dcons_init_port(0, offset, size1, buf, sc);
	offset += size1;
	dcons_init_port(1, offset, size0 - size1, buf, sc);
	buf->version = htonl(DCONS_VERSION);
	buf->magic = ntohl(DCONS_MAGIC);
}