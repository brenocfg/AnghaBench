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
struct seq_file {int dummy; } ;
struct key {char* description; } ;
struct asymmetric_key_subtype {int /*<<< orphan*/  (* describe ) (struct key const*,struct seq_file*) ;} ;
struct asymmetric_key_ids {struct asymmetric_key_id** id; } ;
struct asymmetric_key_id {int len; unsigned char* data; } ;

/* Variables and functions */
 struct asymmetric_key_ids* asymmetric_key_ids (struct key const*) ; 
 struct asymmetric_key_subtype* asymmetric_key_subtype (struct key const*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int,unsigned char const*) ; 
 int /*<<< orphan*/  seq_putc (struct seq_file*,char) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 
 int /*<<< orphan*/  stub1 (struct key const*,struct seq_file*) ; 

__attribute__((used)) static void asymmetric_key_describe(const struct key *key, struct seq_file *m)
{
	const struct asymmetric_key_subtype *subtype = asymmetric_key_subtype(key);
	const struct asymmetric_key_ids *kids = asymmetric_key_ids(key);
	const struct asymmetric_key_id *kid;
	const unsigned char *p;
	int n;

	seq_puts(m, key->description);

	if (subtype) {
		seq_puts(m, ": ");
		subtype->describe(key, m);

		if (kids && kids->id[1]) {
			kid = kids->id[1];
			seq_putc(m, ' ');
			n = kid->len;
			p = kid->data;
			if (n > 4) {
				p += n - 4;
				n = 4;
			}
			seq_printf(m, "%*phN", n, p);
		}

		seq_puts(m, " [");
		/* put something here to indicate the key's capabilities */
		seq_putc(m, ']');
	}
}