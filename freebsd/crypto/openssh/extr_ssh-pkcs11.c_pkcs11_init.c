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

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int pkcs11_interactive ; 
 int /*<<< orphan*/  pkcs11_providers ; 

int
pkcs11_init(int interactive)
{
	pkcs11_interactive = interactive;
	TAILQ_INIT(&pkcs11_providers);
	return (0);
}