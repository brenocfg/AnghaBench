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
struct TYPE_3__ {char* filename; int line; char* buff; int /*<<< orphan*/  errors; } ;
typedef  TYPE_1__ dns_config_stream_t ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void dns_config_stream_error (dns_config_stream_t *self, const char *funcname) {
  fprintf (stderr, "File: %s, Line: %d, Function: %s\n", self->filename, self->line, funcname);
  fprintf (stderr, "%s\n", self->buff);
  self->errors++;
}