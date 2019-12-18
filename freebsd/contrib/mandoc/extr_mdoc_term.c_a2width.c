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
struct termp {int dummy; } ;
struct roffsu {int /*<<< orphan*/  scale; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCALE_HS_INIT (struct roffsu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCALE_MAX ; 
 char* a2roffsu (char const*,struct roffsu*,int /*<<< orphan*/ ) ; 
 int term_hen (struct termp const*,struct roffsu*) ; 
 int /*<<< orphan*/  term_strlen (struct termp const*,char const*) ; 

__attribute__((used)) static int
a2width(const struct termp *p, const char *v)
{
	struct roffsu	 su;
	const char	*end;

	end = a2roffsu(v, &su, SCALE_MAX);
	if (end == NULL || *end != '\0') {
		SCALE_HS_INIT(&su, term_strlen(p, v));
		su.scale /= term_strlen(p, "0");
	}
	return term_hen(p, &su);
}