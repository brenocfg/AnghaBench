#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_4__ {int integer; } ;
struct TYPE_3__ {int integer; } ;

/* Variables and functions */
 int ARRAY_LEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEMOEXT ; 
 int /*<<< orphan*/  Q_stricmpn (char*,int /*<<< orphan*/ ,int) ; 
 int atoi (char*) ; 
 TYPE_2__* com_legacyprotocol ; 
 TYPE_1__* com_protocol ; 
 int* demo_protocols ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 char* strrchr (char const*,char) ; 

qboolean FS_IsDemoExt(const char *filename, int namelen)
{
	char *ext_test;
	int index, protocol;

	ext_test = strrchr(filename, '.');
	if(ext_test && !Q_stricmpn(ext_test + 1, DEMOEXT, ARRAY_LEN(DEMOEXT) - 1))
	{
		protocol = atoi(ext_test + ARRAY_LEN(DEMOEXT));

		if(protocol == com_protocol->integer)
			return qtrue;

#ifdef LEGACY_PROTOCOL
		if(protocol == com_legacyprotocol->integer)
			return qtrue;
#endif

		for(index = 0; demo_protocols[index]; index++)
		{
			if(demo_protocols[index] == protocol)
			return qtrue;
		}
	}

	return qfalse;
}