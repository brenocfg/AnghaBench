#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int wchar_t ;
typedef  scalar_t__ ssize_t ;
struct TYPE_4__ {int /*<<< orphan*/  el_infd; } ;
typedef  TYPE_1__ EditLine ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 int /*<<< orphan*/  EL_BUILTIN_GETCFN ; 
 int /*<<< orphan*/  EL_GETCFN ; 
 int /*<<< orphan*/  FIONREAD ; 
 int /*<<< orphan*/  F_GETFL ; 
 int /*<<< orphan*/  F_SETFL ; 
 int O_NDELAY ; 
 int /*<<< orphan*/  el_set (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 scalar_t__ fcntl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ read (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  rl_event_hook () ; 
 int /*<<< orphan*/  stub1 () ; 

__attribute__((used)) static int
_rl_event_read_char(EditLine *el, wchar_t *wc)
{
	char	ch;
	int	n;
	ssize_t num_read = 0;

	ch = '\0';
	*wc = L'\0';
	while (rl_event_hook) {

		(*rl_event_hook)();

#if defined(FIONREAD)
		if (ioctl(el->el_infd, FIONREAD, &n) < 0)
			return -1;
		if (n)
			num_read = read(el->el_infd, &ch, (size_t)1);
		else
			num_read = 0;
#elif defined(F_SETFL) && defined(O_NDELAY)
		if ((n = fcntl(el->el_infd, F_GETFL, 0)) < 0)
			return -1;
		if (fcntl(el->el_infd, F_SETFL, n|O_NDELAY) < 0)
			return -1;
		num_read = read(el->el_infd, &ch, 1);
		if (fcntl(el->el_infd, F_SETFL, n))
			return -1;
#else
		/* not non-blocking, but what you gonna do? */
		num_read = read(el->el_infd, &ch, 1);
		return -1;
#endif

		if (num_read < 0 && errno == EAGAIN)
			continue;
		if (num_read == 0)
			continue;
		break;
	}
	if (!rl_event_hook)
		el_set(el, EL_GETCFN, EL_BUILTIN_GETCFN);
	*wc = (wchar_t)ch;
	return (int)num_read;
}