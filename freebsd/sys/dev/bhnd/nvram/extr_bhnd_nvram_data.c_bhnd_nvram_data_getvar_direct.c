#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct bhnd_nvram_io {int dummy; } ;
typedef  int /*<<< orphan*/  bhnd_nvram_type ;
struct TYPE_3__ {int (* op_getvar_direct ) (struct bhnd_nvram_io*,char const*,void*,size_t*,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ bhnd_nvram_data_class ;

/* Variables and functions */
 int stub1 (struct bhnd_nvram_io*,char const*,void*,size_t*,int /*<<< orphan*/ ) ; 

int
bhnd_nvram_data_getvar_direct(bhnd_nvram_data_class *cls,
    struct bhnd_nvram_io *io, const char *name, void *buf, size_t *len,
    bhnd_nvram_type type)
{
	return (cls->op_getvar_direct(io, name, buf, len, type));
}