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
struct sshbuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_INT_EQ (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASSERT_PTR_NE (struct sshbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sshbuf_free (struct sshbuf*) ; 
 struct sshbuf* sshbuf_new () ; 
 int /*<<< orphan*/  sshbuf_put_cstring (struct sshbuf*,char const*) ; 
 int /*<<< orphan*/  sshbuf_put_stringb (struct sshbuf*,struct sshbuf*) ; 

__attribute__((used)) static void
put_opt(struct sshbuf *b, const char *name, const char *value)
{
	struct sshbuf *sect;

	sect = sshbuf_new();
	ASSERT_PTR_NE(sect, NULL);
	ASSERT_INT_EQ(sshbuf_put_cstring(b, name), 0);
	if (value != NULL)
		ASSERT_INT_EQ(sshbuf_put_cstring(sect, value), 0);
	ASSERT_INT_EQ(sshbuf_put_stringb(b, sect), 0);
	sshbuf_free(sect);
}