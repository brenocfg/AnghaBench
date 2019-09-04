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
struct strbuf {int dummy; } ;
struct rerere_io_file {int /*<<< orphan*/  input; } ;
struct rerere_io {int dummy; } ;

/* Variables and functions */
 int strbuf_getwholeline (struct strbuf*,int /*<<< orphan*/ ,char) ; 

__attribute__((used)) static int rerere_file_getline(struct strbuf *sb, struct rerere_io *io_)
{
	struct rerere_io_file *io = (struct rerere_io_file *)io_;
	return strbuf_getwholeline(sb, io->input, '\n');
}