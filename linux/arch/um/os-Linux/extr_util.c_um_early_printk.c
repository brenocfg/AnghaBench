void um_early_printk(const char *s, unsigned int n)
{
	printf("%.*s", n, s);
}