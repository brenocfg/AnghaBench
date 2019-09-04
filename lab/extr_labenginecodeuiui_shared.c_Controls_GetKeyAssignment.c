#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  (* getBindingBuf ) (int,char*,int) ;} ;

/* Variables and functions */
 TYPE_1__* DC ; 
 int /*<<< orphan*/  Q_stricmp (char*,char*) ; 
 int /*<<< orphan*/  stub1 (int,char*,int) ; 

__attribute__((used)) static void Controls_GetKeyAssignment (char *command, int *twokeys)
{
	int		count;
	int		j;
	char	b[256];

	twokeys[0] = twokeys[1] = -1;
	count = 0;

	for ( j = 0; j < 256; j++ )
	{
		DC->getBindingBuf( j, b, 256 );
		if ( *b == 0 ) {
			continue;
		}
		if ( !Q_stricmp( b, command ) ) {
			twokeys[count] = j;
			count++;
			if (count == 2) {
				break;
			}
		}
	}
}