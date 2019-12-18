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
typedef  char uint8_t ;
struct bhnd_nvram_io {int dummy; } ;

/* Variables and functions */
 scalar_t__ bhnd_nv_isspace (char) ; 
 int bhnd_nvram_btxt_seek_eol (struct bhnd_nvram_io*,size_t*) ; 
 int bhnd_nvram_io_read_ptr (struct bhnd_nvram_io*,size_t,void const**,int /*<<< orphan*/ ,size_t*) ; 

__attribute__((used)) static int
bhnd_nvram_btxt_seek_next(struct bhnd_nvram_io *io, size_t *offset)
{
	const uint8_t	*baseptr, *p;
	const void	*rbuf;
	size_t		 nbytes;
	int		 error;

	/* Fetch read buffer */
	if ((error = bhnd_nvram_io_read_ptr(io, *offset, &rbuf, 0, &nbytes)))
		return (error);

	/* Skip leading whitespace and comments */
	baseptr = rbuf;
	p = rbuf;
	while ((size_t)(p - baseptr) < nbytes) {
		char c = *p;

		/* Skip whitespace */
		if (bhnd_nv_isspace(c)) {
			p++;
			continue;
		}

		/* Skip entire comment line */
		if (c == '#') {
			size_t line_off = *offset + (p - baseptr);
	
			if ((error = bhnd_nvram_btxt_seek_eol(io, &line_off)))
				return (error);

			p = baseptr + (line_off - *offset);
			continue;
		}

		/* Non-whitespace, non-comment */
		break;
	}

	*offset += (p - baseptr);
	return (0);
}