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
struct aw_ir_softc {scalar_t__ dcnt; } ;

/* Variables and functions */
 scalar_t__ AW_IR_RAW_BUF_SIZE ; 

__attribute__((used)) static int
aw_ir_buf_full(struct aw_ir_softc *sc)
{

	return (sc->dcnt >= AW_IR_RAW_BUF_SIZE);
}