#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct _memstream {int dummy; } ;
struct TYPE_4__ {char const* str; } ;
struct TYPE_5__ {TYPE_1__ u; } ;
typedef  TYPE_2__ _citrus_prop_object_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
#define  EOF 128 
 size_t _CITRUS_PROP_STR_BUFSIZ ; 
 scalar_t__ _bcs_isspace (int) ; 
 int _citrus_prop_read_character_common (struct _memstream*,int*) ; 
 int _memstream_getc (struct _memstream*) ; 
 int /*<<< orphan*/  _memstream_skip_ws (struct _memstream*) ; 
 int /*<<< orphan*/  _memstream_ungetc (struct _memstream*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (size_t) ; 
 char* realloc (char*,size_t) ; 

__attribute__((used)) static int
_citrus_prop_read_str(struct _memstream * __restrict ms,
    _citrus_prop_object_t * __restrict obj)
{
	int ch, errnum, quot;
	char *s, *t;
#define _CITRUS_PROP_STR_BUFSIZ	512
	size_t m, n;

	m = _CITRUS_PROP_STR_BUFSIZ;
	s = malloc(m);
	if (s == NULL)
		return (ENOMEM);
	n = 0;
	_memstream_skip_ws(ms);
	quot = _memstream_getc(ms);
	switch (quot) {
	case EOF:
		goto done;
		/*NOTREACHED*/
	case '\\':
		_memstream_ungetc(ms, quot);
		quot = EOF;
		/*FALLTHROUGH*/
	case '\"': case '\'':
		break;
	default:
		s[n] = quot;
		++n, --m;
		quot = EOF;
	}
	for (;;) {
		if (m < 1) {
			m = _CITRUS_PROP_STR_BUFSIZ;
			t = realloc(s, n + m);
			if (t == NULL) {
				free(s);
				return (ENOMEM);
			}
			s = t;
		}
		ch = _memstream_getc(ms);
		if (quot == ch || (quot == EOF &&
		    (ch == ';' || _bcs_isspace(ch)))) {
done:
			s[n] = '\0';
			obj->u.str = (const char *)s;
			return (0);
		}
		_memstream_ungetc(ms, ch);
		errnum = _citrus_prop_read_character_common(ms, &ch);
		if (errnum != 0) {
			free(s);
			return (errnum);
		}
		s[n] = ch;
		++n, --m;
	}
	free(s);
	return (EINVAL);
#undef _CITRUS_PROP_STR_BUFSIZ
}