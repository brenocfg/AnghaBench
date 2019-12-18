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
struct aw_ir_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AW_IR_RXFIFO ; 
 int READ (struct aw_ir_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned char
aw_ir_read_data(struct aw_ir_softc *sc)
{

	return (unsigned char)(READ(sc, AW_IR_RXFIFO) & 0xff);
}