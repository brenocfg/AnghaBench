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
struct TYPE_2__ {int /*<<< orphan*/  file; } ;
struct config_source {TYPE_1__ u; } ;

/* Variables and functions */
 long ftell (int /*<<< orphan*/ ) ; 

__attribute__((used)) static long config_file_ftell(struct config_source *conf)
{
	return ftell(conf->u.file);
}