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
typedef  int /*<<< orphan*/  linker_file_t ;
typedef  int /*<<< orphan*/  linker_ctf_t ;

/* Variables and functions */
 int LINKER_CTF_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
linker_ctf_get(linker_file_t file, linker_ctf_t *lc)
{
	return (LINKER_CTF_GET(file, lc));
}