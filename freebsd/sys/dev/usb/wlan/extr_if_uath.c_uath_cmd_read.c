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
typedef  int /*<<< orphan*/  uint32_t ;
struct uath_softc {int dummy; } ;

/* Variables and functions */
 int UATH_CMD_FLAG_READ ; 
 int uath_cmdsend (struct uath_softc*,int /*<<< orphan*/ ,void const*,int,void*,int,int) ; 

__attribute__((used)) static int
uath_cmd_read(struct uath_softc *sc, uint32_t code, const void *idata,
    int ilen, void *odata, int olen, int flags)
{

	flags |= UATH_CMD_FLAG_READ;
	return uath_cmdsend(sc, code, idata, ilen, odata, olen, flags);
}