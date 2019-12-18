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
struct TYPE_2__ {char mode; int /*<<< orphan*/  fname; scalar_t__ fp; } ;

/* Variables and functions */
 int EOF ; 
 int FOPEN_MAX ; 
 char LE ; 
 int /*<<< orphan*/  WARNING (char*,int /*<<< orphan*/ ) ; 
 int fclose (scalar_t__) ; 
 scalar_t__ ferror (scalar_t__) ; 
 TYPE_1__* files ; 
 int pclose (scalar_t__) ; 

void closeall(void)
{
	int i, stat;

	for (i = 0; i < FOPEN_MAX; i++) {
		if (files[i].fp) {
			if (ferror(files[i].fp))
				WARNING( "i/o error occurred on %s", files[i].fname );
			if (files[i].mode == '|' || files[i].mode == LE)
				stat = pclose(files[i].fp);
			else
				stat = fclose(files[i].fp);
			if (stat == EOF)
				WARNING( "i/o error occurred while closing %s", files[i].fname );
		}
	}
}