__attribute__((used)) static void *wcput(int c, void *cl) {
	unsigned int *s = cl;

	*s++ = c;
	return s;
}