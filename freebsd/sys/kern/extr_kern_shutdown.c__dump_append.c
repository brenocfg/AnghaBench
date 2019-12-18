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
typedef  int /*<<< orphan*/  vm_offset_t ;
struct dumperinfo {size_t dumpoff; int /*<<< orphan*/ * kdcrypto; } ;

/* Variables and functions */
 int dump_encrypted_write (struct dumperinfo*,void*,int /*<<< orphan*/ ,size_t,size_t) ; 
 int dump_write (struct dumperinfo*,void*,int /*<<< orphan*/ ,size_t,size_t) ; 

__attribute__((used)) static int
_dump_append(struct dumperinfo *di, void *virtual, vm_offset_t physical,
    size_t length)
{
	int error;

#ifdef EKCD
	if (di->kdcrypto != NULL)
		error = dump_encrypted_write(di, virtual, physical, di->dumpoff,
		    length);
	else
#endif
		error = dump_write(di, virtual, physical, di->dumpoff, length);
	if (error == 0)
		di->dumpoff += length;
	return (error);
}