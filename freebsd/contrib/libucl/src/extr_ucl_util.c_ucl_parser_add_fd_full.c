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
struct ucl_parser {int /*<<< orphan*/ * cur_file; int /*<<< orphan*/  err; } ;
struct stat {size_t st_size; } ;
typedef  enum ucl_parse_type { ____Placeholder_ucl_parse_type } ucl_parse_type ;
typedef  enum ucl_duplicate_strategy { ____Placeholder_ucl_duplicate_strategy } ucl_duplicate_strategy ;

/* Variables and functions */
 unsigned char* MAP_FAILED ; 
 int /*<<< orphan*/  MAP_SHARED ; 
 int /*<<< orphan*/  PROT_READ ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int fstat (int,struct stat*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ucl_create_err (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 unsigned char* ucl_mmap (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ucl_munmap (unsigned char*,size_t) ; 
 int ucl_parser_add_chunk_full (struct ucl_parser*,unsigned char*,size_t,unsigned int,int,int) ; 

bool
ucl_parser_add_fd_full (struct ucl_parser *parser, int fd,
		unsigned priority, enum ucl_duplicate_strategy strat,
		enum ucl_parse_type parse_type)
{
	unsigned char *buf;
	size_t len;
	bool ret;
	struct stat st;

	if (fstat (fd, &st) == -1) {
		ucl_create_err (&parser->err, "cannot stat fd %d: %s",
			fd, strerror (errno));
		return false;
	}
	if (st.st_size == 0) {
		return true;
	}
	if ((buf = ucl_mmap (NULL, st.st_size, PROT_READ, MAP_SHARED, fd, 0)) == MAP_FAILED) {
		ucl_create_err (&parser->err, "cannot mmap fd %d: %s",
			fd, strerror (errno));
		return false;
	}

	if (parser->cur_file) {
		free (parser->cur_file);
	}
	parser->cur_file = NULL;
	len = st.st_size;
	ret = ucl_parser_add_chunk_full (parser, buf, len, priority, strat,
			parse_type);

	if (len > 0) {
		ucl_munmap (buf, len);
	}

	return ret;
}