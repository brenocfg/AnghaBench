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
typedef  int /*<<< orphan*/  u32 ;
struct ar8xxx_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR8216_REG_PORT_STATUS (int) ; 
 int /*<<< orphan*/  ar8xxx_read (struct ar8xxx_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32
ar8216_read_port_status(struct ar8xxx_priv *priv, int port)
{
	return ar8xxx_read(priv, AR8216_REG_PORT_STATUS(port));
}