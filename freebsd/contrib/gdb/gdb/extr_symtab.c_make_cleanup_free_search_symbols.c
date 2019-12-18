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
struct symbol_search {int dummy; } ;
struct cleanup {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  do_free_search_symbols_cleanup ; 
 struct cleanup* make_cleanup (int /*<<< orphan*/ ,struct symbol_search*) ; 

struct cleanup *
make_cleanup_free_search_symbols (struct symbol_search *symbols)
{
  return make_cleanup (do_free_search_symbols_cleanup, symbols);
}