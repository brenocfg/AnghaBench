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
struct config_file {scalar_t__* log_identity; } ;

/* Variables and functions */
 int /*<<< orphan*/  log_ident_set (char const*) ; 

__attribute__((used)) static void
log_ident_set_fromdefault(struct config_file* cfg,
	const char *log_default_identity)
{
	if(cfg->log_identity == NULL || cfg->log_identity[0] == 0)
		log_ident_set(log_default_identity);
	else
		log_ident_set(cfg->log_identity);
}